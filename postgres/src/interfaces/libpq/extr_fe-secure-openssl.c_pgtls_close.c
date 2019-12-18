#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ssl_in_use; int /*<<< orphan*/ * engine; int /*<<< orphan*/ * peer; int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_ssl_system () ; 

void
pgtls_close(PGconn *conn)
{
	bool		destroy_needed = false;

	if (conn->ssl)
	{
		/*
		 * We can't destroy everything SSL-related here due to the possible
		 * later calls to OpenSSL routines which may need our thread
		 * callbacks, so set a flag here and check at the end.
		 */
		destroy_needed = true;

		SSL_shutdown(conn->ssl);
		SSL_free(conn->ssl);
		conn->ssl = NULL;
		conn->ssl_in_use = false;
	}

	if (conn->peer)
	{
		X509_free(conn->peer);
		conn->peer = NULL;
	}

#ifdef USE_SSL_ENGINE
	if (conn->engine)
	{
		ENGINE_finish(conn->engine);
		ENGINE_free(conn->engine);
		conn->engine = NULL;
	}
#endif

	/*
	 * This will remove our SSL locking hooks, if this is the last SSL
	 * connection, which means we must wait to call it until after all SSL
	 * calls have been made, otherwise we can end up with a race condition and
	 * possible deadlocks.
	 *
	 * See comments above destroy_ssl_system().
	 */
	if (destroy_needed)
		destroy_ssl_system();
}
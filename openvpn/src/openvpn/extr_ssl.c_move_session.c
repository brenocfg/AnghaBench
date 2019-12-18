#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tls_multi {int /*<<< orphan*/ * session; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  D_TLS_DEBUG ; 
 int /*<<< orphan*/  D_TLS_DEBUG_LOW ; 
 int TM_SIZE ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secure_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  session_index_name (int) ; 
 int /*<<< orphan*/  tls_session_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls_session_init (struct tls_multi*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
move_session(struct tls_multi *multi, int dest, int src, bool reinit_src)
{
    msg(D_TLS_DEBUG_LOW, "TLS: move_session: dest=%s src=%s reinit_src=%d",
        session_index_name(dest),
        session_index_name(src),
        reinit_src);
    ASSERT(src != dest);
    ASSERT(src >= 0 && src < TM_SIZE);
    ASSERT(dest >= 0 && dest < TM_SIZE);
    tls_session_free(&multi->session[dest], false);
    multi->session[dest] = multi->session[src];

    if (reinit_src)
    {
        tls_session_init(multi, &multi->session[src]);
    }
    else
    {
        secure_memzero(&multi->session[src], sizeof(multi->session[src]));
    }

    dmsg(D_TLS_DEBUG, "TLS: move_session: exit");
}
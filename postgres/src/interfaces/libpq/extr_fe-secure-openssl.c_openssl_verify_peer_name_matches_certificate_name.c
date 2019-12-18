#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 unsigned char* ASN1_STRING_data (int /*<<< orphan*/ *) ; 
 unsigned char* ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int pq_verify_peer_name_matches_certificate_name (TYPE_1__*,char const*,int,char**) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
openssl_verify_peer_name_matches_certificate_name(PGconn *conn, ASN1_STRING *name_entry,
												  char **store_name)
{
	int			len;
	const unsigned char *namedata;

	/* Should not happen... */
	if (name_entry == NULL)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("SSL certificate's name entry is missing\n"));
		return -1;
	}

	/*
	 * GEN_DNS can be only IA5String, equivalent to US ASCII.
	 */
#ifdef HAVE_ASN1_STRING_GET0_DATA
	namedata = ASN1_STRING_get0_data(name_entry);
#else
	namedata = ASN1_STRING_data(name_entry);
#endif
	len = ASN1_STRING_length(name_entry);

	/* OK to cast from unsigned to plain char, since it's all ASCII. */
	return pq_verify_peer_name_matches_certificate_name(conn, (const char *) namedata, len, store_name);
}
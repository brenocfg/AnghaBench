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
struct TYPE_3__ {scalar_t__ peer; } ;
typedef  TYPE_1__ Port ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_to_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* BN_bn2dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/ * X509_get_serialNumber (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

void
be_tls_get_peer_serial(Port *port, char *ptr, size_t len)
{
	if (port->peer)
	{
		ASN1_INTEGER *serial;
		BIGNUM	   *b;
		char	   *decimal;

		serial = X509_get_serialNumber(port->peer);
		b = ASN1_INTEGER_to_BN(serial, NULL);
		decimal = BN_bn2dec(b);

		BN_free(b);
		strlcpy(ptr, decimal, len);
		OPENSSL_free(decimal);
	}
	else
		ptr[0] = '\0';
}
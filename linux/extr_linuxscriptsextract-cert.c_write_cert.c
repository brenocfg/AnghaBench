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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 scalar_t__ BIO_new_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_oneline (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cert_dst ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  i2d_X509_bio (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ kbuild_verbose ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ wb ; 

__attribute__((used)) static void write_cert(X509 *x509)
{
	char buf[200];

	if (!wb) {
		wb = BIO_new_file(cert_dst, "wb");
		ERR(!wb, "%s", cert_dst);
	}
	X509_NAME_oneline(X509_get_subject_name(x509), buf, sizeof(buf));
	ERR(!i2d_X509_bio(wb, x509), "%s", cert_dst);
	if (kbuild_verbose)
		fprintf(stderr, "Extracted cert: %s\n", buf);
}
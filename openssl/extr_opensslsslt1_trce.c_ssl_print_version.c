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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_trace_str (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_version_tbl ; 

__attribute__((used)) static int ssl_print_version(BIO *bio, int indent, const char *name,
                             const unsigned char **pmsg, size_t *pmsglen,
                             unsigned int *version)
{
    int vers;

    if (*pmsglen < 2)
        return 0;
    vers = ((*pmsg)[0] << 8) | (*pmsg)[1];
    if (version != NULL)
        *version = vers;
    BIO_indent(bio, indent, 80);
    BIO_printf(bio, "%s=0x%x (%s)\n",
               name, vers, ssl_trace_str(vers, ssl_version_tbl));
    *pmsg += 2;
    *pmsglen -= 2;
    return 1;
}
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
typedef  int /*<<< orphan*/  X509_REQ ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_REQ_add1_attr_by_NID (int /*<<< orphan*/ *,int,unsigned long,unsigned char*,int) ; 
 int /*<<< orphan*/  bio_err ; 
 int build_data (char*,char const*,char*,int,int,char*,int,char*,char*) ; 

__attribute__((used)) static int add_attribute_object(X509_REQ *req, char *text, const char *def,
                                char *value, int nid, int n_min,
                                int n_max, unsigned long chtype)
{
    int ret = 0;
    char buf[1024];

    ret = build_data(text, def, value, n_min, n_max, buf, sizeof(buf),
                     "Attribute value", "Attribute default");
    if ((ret == 0) || (ret == 1))
        return ret;
    ret = 1;

    if (!X509_REQ_add1_attr_by_NID(req, nid, chtype,
                                   (unsigned char *)buf, -1)) {
        BIO_printf(bio_err, "Error adding attribute\n");
        ERR_print_errors(bio_err);
        ret = 0;
    }

    return ret;
}
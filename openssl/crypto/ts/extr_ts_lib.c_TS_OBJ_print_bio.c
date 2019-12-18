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
typedef  int /*<<< orphan*/  obj_txt ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  OBJ_obj2txt (char*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int TS_OBJ_print_bio(BIO *bio, const ASN1_OBJECT *obj)
{
    char obj_txt[128];

    OBJ_obj2txt(obj_txt, sizeof(obj_txt), obj, 0);
    BIO_printf(bio, "%s\n", obj_txt);

    return 1;
}
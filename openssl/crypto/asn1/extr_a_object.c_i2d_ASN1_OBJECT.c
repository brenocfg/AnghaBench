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
struct TYPE_3__ {int length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_I2D_ASN1_OBJECT ; 
 int ASN1_object_size (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_put_object (unsigned char**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  V_ASN1_OBJECT ; 
 int /*<<< orphan*/  V_ASN1_UNIVERSAL ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 

int i2d_ASN1_OBJECT(const ASN1_OBJECT *a, unsigned char **pp)
{
    unsigned char *p, *allocated = NULL;
    int objsize;

    if ((a == NULL) || (a->data == NULL))
        return 0;

    objsize = ASN1_object_size(0, a->length, V_ASN1_OBJECT);
    if (pp == NULL || objsize == -1)
        return objsize;

    if (*pp == NULL) {
        if ((p = allocated = OPENSSL_malloc(objsize)) == NULL) {
            ASN1err(ASN1_F_I2D_ASN1_OBJECT, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    } else {
        p = *pp;
    }

    ASN1_put_object(&p, 0, a->length, V_ASN1_OBJECT, V_ASN1_UNIVERSAL);
    memcpy(p, a->data, a->length);

    /*
     * If a new buffer was allocated, just return it back.
     * If not, return the incremented buffer pointer.
     */
    *pp = allocated != NULL ? allocated : p + a->length;
    return objsize;
}
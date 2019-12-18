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
struct object_st {struct object_st* p4; int /*<<< orphan*/ * p3; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (struct object_st*) ; 

__attribute__((used)) static void cleanup_object(void *vobj)
{
    struct object_st *obj = vobj;

    BN_free(obj->p3);
    obj->p3 = NULL;
    OPENSSL_free(obj->p4);
    obj->p4 = NULL;
    OPENSSL_free(obj);
}
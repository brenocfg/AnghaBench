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

/* Variables and functions */
 int /*<<< orphan*/  EVP_PBE_cleanup () ; 
 int OBJ_NAME_TYPE_CIPHER_METH ; 
 int OBJ_NAME_TYPE_KDF_METH ; 
 int OBJ_NAME_TYPE_MD_METH ; 
 int /*<<< orphan*/  OBJ_NAME_cleanup (int) ; 
 int /*<<< orphan*/  OBJ_sigid_free () ; 
 int /*<<< orphan*/  evp_app_cleanup_int () ; 

void evp_cleanup_int(void)
{
    OBJ_NAME_cleanup(OBJ_NAME_TYPE_KDF_METH);
    OBJ_NAME_cleanup(OBJ_NAME_TYPE_CIPHER_METH);
    OBJ_NAME_cleanup(OBJ_NAME_TYPE_MD_METH);
    /*
     * The above calls will only clean out the contents of the name hash
     * table, but not the hash table itself.  The following line does that
     * part.  -- Richard Levitte
     */
    OBJ_NAME_cleanup(-1);

    EVP_PBE_cleanup();
    OBJ_sigid_free();

    evp_app_cleanup_int();
}
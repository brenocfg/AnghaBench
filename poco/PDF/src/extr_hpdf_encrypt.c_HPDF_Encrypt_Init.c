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
struct TYPE_4__ {int key_len; int permission; int /*<<< orphan*/  user_passwd; int /*<<< orphan*/  owner_passwd; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  HPDF_Encrypt_Rec ;
typedef  TYPE_1__* HPDF_Encrypt ;

/* Variables and functions */
 int HPDF_ENABLE_COPY ; 
 int HPDF_ENABLE_EDIT ; 
 int HPDF_ENABLE_EDIT_ALL ; 
 int HPDF_ENABLE_PRINT ; 
 int /*<<< orphan*/  HPDF_ENCRYPT_R2 ; 
 int /*<<< orphan*/  HPDF_MemCpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_PADDING_STRING ; 
 int /*<<< orphan*/  HPDF_PASSWD_LEN ; 
 int HPDF_PERMISSION_PAD ; 

void
HPDF_Encrypt_Init  (HPDF_Encrypt  attr)
{
    HPDF_MemSet (attr, 0, sizeof(HPDF_Encrypt_Rec));
    attr->mode = HPDF_ENCRYPT_R2;
    attr->key_len = 5;
    HPDF_MemCpy (attr->owner_passwd, HPDF_PADDING_STRING, HPDF_PASSWD_LEN);
    HPDF_MemCpy (attr->user_passwd, HPDF_PADDING_STRING, HPDF_PASSWD_LEN);
    attr->permission = HPDF_ENABLE_PRINT | HPDF_ENABLE_EDIT_ALL |
        HPDF_ENABLE_COPY | HPDF_ENABLE_EDIT | HPDF_PERMISSION_PAD;
}
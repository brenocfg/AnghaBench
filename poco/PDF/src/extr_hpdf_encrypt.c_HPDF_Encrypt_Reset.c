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
struct TYPE_3__ {scalar_t__ key_len; int /*<<< orphan*/  md5_encryption_key; int /*<<< orphan*/  arc4ctx; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_Encrypt ;

/* Variables and functions */
 int /*<<< orphan*/  ARC4Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HPDF_ENCRYPT_KEY_MAX ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_Encrypt_Reset  (HPDF_Encrypt  attr)
{
    HPDF_UINT key_len = (attr->key_len + 5 > HPDF_ENCRYPT_KEY_MAX) ?
                    HPDF_ENCRYPT_KEY_MAX : attr->key_len + 5;

    HPDF_PTRACE((" HPDF_Encrypt_Reset\n"));

    ARC4Init(&attr->arc4ctx, attr->md5_encryption_key, key_len);
}
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
 int /*<<< orphan*/  AES_PRIV_SIZE ; 
 int /*<<< orphan*/  _rtw_memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_mfree (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aes_encrypt_deinit(void *ctx)
{
	_rtw_memset(ctx, 0, AES_PRIV_SIZE);
	rtw_mfree(ctx, AES_PRIV_SIZE);
}
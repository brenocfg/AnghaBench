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
struct TYPE_3__ {int /*<<< orphan*/  md5_buf; int /*<<< orphan*/  md5_std; int /*<<< orphan*/  md5_stc; int /*<<< orphan*/  md5_stb; int /*<<< orphan*/  md5_sta; scalar_t__ md5_i; scalar_t__ md5_n; } ;
typedef  TYPE_1__ md5_ctxt ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_A0 ; 
 int /*<<< orphan*/  MD5_B0 ; 
 int /*<<< orphan*/  MD5_C0 ; 
 int /*<<< orphan*/  MD5_D0 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
md5_init(md5_ctxt *ctxt)
{
	ctxt->md5_n = 0;
	ctxt->md5_i = 0;
	ctxt->md5_sta = MD5_A0;
	ctxt->md5_stb = MD5_B0;
	ctxt->md5_stc = MD5_C0;
	ctxt->md5_std = MD5_D0;
	memset(ctxt->md5_buf, 0, sizeof(ctxt->md5_buf));
}
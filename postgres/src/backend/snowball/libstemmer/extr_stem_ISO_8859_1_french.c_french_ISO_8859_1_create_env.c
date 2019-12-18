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
struct SN_env {int dummy; } ;

/* Variables and functions */
 struct SN_env* SN_create_env (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

extern struct SN_env * french_ISO_8859_1_create_env(void) { return SN_create_env(0, 3, 0); }
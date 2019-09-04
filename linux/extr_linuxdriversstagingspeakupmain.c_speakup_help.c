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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KT_SPKUP ; 
 int /*<<< orphan*/  SPEAKUP_HELP ; 
 int /*<<< orphan*/  spk_handle_help (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void speakup_help(struct vc_data *vc)
{
	spk_handle_help(vc, KT_SPKUP, SPEAKUP_HELP, 0);
}
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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entropy_rotate ; 
 int /*<<< orphan*/  rotatePanelCmds (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void rotateEntropyHCb(void *user, bool rev) {
	RCore *core = (RCore *)user;
	rotatePanelCmds (core, entropy_rotate, COUNT (entropy_rotate), "p==", rev);
}
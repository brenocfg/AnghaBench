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
typedef  int /*<<< orphan*/  RLinePromptType ;
typedef  int /*<<< orphan*/  RLineCompletion ;
typedef  int /*<<< orphan*/  RLineBuffer ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_autocomplete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int autocomplete(RLineCompletion *completion, RLineBuffer *buf, RLinePromptType prompt_type, void *user) {
	RCore *core = user;
	r_core_autocomplete (core, completion, buf, prompt_type);
	return true;
}
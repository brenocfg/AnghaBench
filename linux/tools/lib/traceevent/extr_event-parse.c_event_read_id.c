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
 int /*<<< orphan*/  TEP_EVENT_ITEM ; 
 int /*<<< orphan*/  TEP_EVENT_OP ; 
 int /*<<< orphan*/  free_token (char*) ; 
 scalar_t__ read_expect_type (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ read_expected (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_expected_item (int /*<<< orphan*/ ,char*) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int event_read_id(void)
{
	char *token;
	int id;

	if (read_expected_item(TEP_EVENT_ITEM, "ID") < 0)
		return -1;

	if (read_expected(TEP_EVENT_OP, ":") < 0)
		return -1;

	if (read_expect_type(TEP_EVENT_ITEM, &token) < 0)
		goto fail;

	id = strtoul(token, NULL, 0);
	free_token(token);
	return id;

 fail:
	free_token(token);
	return -1;
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct exofs_dev {scalar_t__ urilen; int /*<<< orphan*/ * uri; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * krealloc (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,char const*,scalar_t__) ; 

__attribute__((used)) static ssize_t uri_store(struct exofs_dev *edp, const char *buf, size_t len)
{
	uint8_t *new_uri;

	edp->urilen = strlen(buf) + 1;
	new_uri = krealloc(edp->uri, edp->urilen, GFP_KERNEL);
	if (new_uri == NULL)
		return -ENOMEM;
	edp->uri = new_uri;
	strncpy(edp->uri, buf, edp->urilen);
	return edp->urilen;
}
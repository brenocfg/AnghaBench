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
struct annotated_source {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct annotated_source* zalloc (int) ; 

__attribute__((used)) static struct annotated_source *annotated_source__new(void)
{
	struct annotated_source *src = zalloc(sizeof(*src));

	if (src != NULL)
		INIT_LIST_HEAD(&src->source);

	return src;
}
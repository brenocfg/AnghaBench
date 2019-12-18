#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct taskdialog_template_desc {TYPE_1__* taskconfig; } ;
struct TYPE_2__ {int /*<<< orphan*/  pszContent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID_CONTENT ; 
 unsigned int taskdialog_add_static_label (struct taskdialog_template_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int taskdialog_add_content(struct taskdialog_template_desc *desc)
{
    return taskdialog_add_static_label(desc, ID_CONTENT, desc->taskconfig->pszContent);
}
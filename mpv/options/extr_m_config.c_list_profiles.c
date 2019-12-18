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
struct m_profile {char* desc; int /*<<< orphan*/  name; struct m_profile* next; } ;
struct m_config {struct m_profile* profiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (struct m_config*,char*,...) ; 

__attribute__((used)) static void list_profiles(struct m_config *config)
{
    MP_INFO(config, "Available profiles:\n");
    for (struct m_profile *p = config->profiles; p; p = p->next)
        MP_INFO(config, "\t%s\t%s\n", p->name, p->desc ? p->desc : "");
    MP_INFO(config, "\n");
}
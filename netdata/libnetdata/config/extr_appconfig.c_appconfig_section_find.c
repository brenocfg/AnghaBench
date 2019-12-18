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
struct section {int dummy; } ;
struct config {int dummy; } ;

/* Variables and functions */
 struct section* appconfig_index_find (struct config*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct section *appconfig_section_find(struct config *root, const char *section) {
    return appconfig_index_find(root, section, 0);
}
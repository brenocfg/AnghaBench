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
struct ubifs_info {scalar_t__ authenticated; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_UBIFS_FS_AUTHENTICATION ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ubifs_authenticated(const struct ubifs_info *c)
{
	return (IS_ENABLED(CONFIG_UBIFS_FS_AUTHENTICATION)) && c->authenticated;
}
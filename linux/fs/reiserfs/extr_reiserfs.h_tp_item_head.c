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
struct treepath {int dummy; } ;
struct item_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_LAST_POSITION (struct treepath const*) ; 
 int /*<<< orphan*/  PATH_PLAST_BUFFER (struct treepath const*) ; 
 struct item_head* item_head (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct item_head *tp_item_head(const struct treepath *path)
{
	return item_head(PATH_PLAST_BUFFER(path), PATH_LAST_POSITION(path));
}
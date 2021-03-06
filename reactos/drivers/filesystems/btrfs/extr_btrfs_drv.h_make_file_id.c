#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int id; } ;
typedef  TYPE_1__ root ;

/* Variables and functions */

__attribute__((used)) static __inline uint64_t make_file_id(root* r, uint64_t inode) {
    return (r->id << 40) | (inode & 0xffffffffff);
}
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
struct extent_status {int dummy; } ;

/* Variables and functions */
 int EXTENT_STATUS_HOLE ; 
 int ext4_es_type (struct extent_status*) ; 

__attribute__((used)) static inline int ext4_es_is_hole(struct extent_status *es)
{
	return (ext4_es_type(es) & EXTENT_STATUS_HOLE) != 0;
}
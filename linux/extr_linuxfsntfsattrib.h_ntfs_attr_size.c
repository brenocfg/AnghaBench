#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_7__ {int /*<<< orphan*/  data_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  value_length; } ;
struct TYPE_8__ {TYPE_2__ non_resident; TYPE_1__ resident; } ;
struct TYPE_9__ {TYPE_3__ data; int /*<<< orphan*/  non_resident; } ;
typedef  TYPE_4__ ATTR_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sle64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline s64 ntfs_attr_size(const ATTR_RECORD *a)
{
	if (!a->non_resident)
		return (s64)le32_to_cpu(a->data.resident.value_length);
	return sle64_to_cpu(a->data.non_resident.data_size);
}
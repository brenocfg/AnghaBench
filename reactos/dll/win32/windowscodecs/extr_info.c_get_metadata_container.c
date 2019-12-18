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
struct metadata_container {int dummy; } ;
struct TYPE_3__ {unsigned int container_count; struct metadata_container* containers; scalar_t__ container_formats; } ;
typedef  TYPE_1__ MetadataReaderInfo ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ IsEqualGUID (scalar_t__,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct metadata_container *get_metadata_container(MetadataReaderInfo *info, const GUID *guid)
{
    unsigned i;

    for (i = 0; i < info->container_count; i++)
        if (IsEqualGUID(info->container_formats + i, guid))
            return info->containers + i;

    return NULL;
}
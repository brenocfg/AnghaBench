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
struct TYPE_3__ {int /*<<< orphan*/  version; int /*<<< orphan*/  clsid; } ;
typedef  int /*<<< orphan*/  MSXML_VERSION ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSXML_DEFAULT ; 
 TYPE_1__* clsid_versions_table ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static MSXML_VERSION get_msxml_version(const GUID *clsid)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(clsid_versions_table); i++)
        if (IsEqualGUID(clsid, clsid_versions_table[i].clsid))
            return clsid_versions_table[i].version;

    ERR("unknown clsid=%s\n", debugstr_guid(clsid));
    return MSXML_DEFAULT;
}
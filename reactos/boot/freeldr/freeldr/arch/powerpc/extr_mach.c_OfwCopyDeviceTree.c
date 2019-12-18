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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PCONFIGURATION_COMPONENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  AdapterClass ; 
 int /*<<< orphan*/  FldrCreateComponentKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MultiFunctionAdapter ; 
 int /*<<< orphan*/  NarrowToWide (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OfwHandleDiskController (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OfwHandleDiskObject (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ofw_child (int) ; 
 int /*<<< orphan*/  ofw_getprop (int,char*,char*,int) ; 
 int ofw_getproplen (int,char*) ; 
 int ofw_nextprop (int,char*,char*) ; 
 int /*<<< orphan*/  ofw_package_to_path (int,char*,int) ; 
 int ofw_peer (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strrchr (char*,char) ; 

VOID OfwCopyDeviceTree
(PCONFIGURATION_COMPONENT_DATA ParentKey,
 char *name,
 int innode,
 ULONG *BusNumber,
 ULONG *DiskController,
 ULONG *DiskNumber)
{
    int proplen = 0, node = innode;
    char *prev_name, cur_name[64], data[256], *slash, devtype[64];
    wchar_t wide_name[64];
    PCONFIGURATION_COMPONENT_DATA NewKey;

    NarrowToWide(wide_name, name);

    /* Create a key for this device */
    FldrCreateComponentKey
        (ParentKey,
         AdapterClass,
         MultiFunctionAdapter,
         0,
         0,
         (ULONG)-1,
         NULL,
         NULL,
         0,
         &NewKey);

    /* Add properties */
    for (prev_name = ""; ofw_nextprop(node, prev_name, cur_name) == 1; )
    {
        proplen = ofw_getproplen(node, cur_name);
        if (proplen > 256 || proplen < 0)
        {
            printf("Warning: not getting prop %s (too long: %d)\n",
                   cur_name, proplen);
            continue;
        }
        ofw_getprop(node, cur_name, data, sizeof(data));

        /* Get device type so we can examine it */
        if (!strcmp(cur_name, "device_type"))
            strcpy(devtype, (char *)data);

        NarrowToWide(wide_name, cur_name);
        //RegSetValue(NewKey, wide_name, REG_BINARY, data, proplen);

        strcpy(data, cur_name);
        prev_name = data;
    }

#if 0
    /* Special device handling */
    if (!strcmp(devtype, "ata"))
    {
        OfwHandleDiskController(NewKey, node, *DiskController);
        (*DiskController)++;
        *DiskNumber = 0;
    }
    else if (!strcmp(devtype, "disk"))
    {
        OfwHandleDiskObject(NewKey, node, *DiskController, *DiskNumber);
        (*DiskNumber)++;
    }
#endif

    /* Subdevices */
    for (node = ofw_child(node); node; node = ofw_peer(node))
    {
        ofw_package_to_path(node, data, sizeof(data));
        slash = strrchr(data, '/');
        if (slash) slash++; else continue;
        OfwCopyDeviceTree
            (NewKey, slash, node, BusNumber, DiskController, DiskNumber);
    }
}
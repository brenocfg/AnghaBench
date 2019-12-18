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

/* Variables and functions */
#define  FileFsAttributeInformation 135 
#define  FileFsControlInformation 134 
#define  FileFsDeviceInformation 133 
#define  FileFsDriverPathInformation 132 
#define  FileFsFullSizeInformation 131 
#define  FileFsObjectIdInformation 130 
#define  FileFsSizeInformation 129 
#define  FileFsVolumeInformation 128 

unsigned char *print_fs_information_class(int InfoClass)
{
    switch (InfoClass) {
        case FileFsAttributeInformation:
            return (unsigned char *)"FileFsAttributeInformation";
        case FileFsControlInformation:
            return (unsigned char *)"FileFsControlInformation";
        case FileFsDeviceInformation:
            return (unsigned char *)"FileFsDeviceInformation";
        case FileFsDriverPathInformation:
            return (unsigned char *)"FileFsDriverPathInformation";
        case FileFsFullSizeInformation:
            return (unsigned char *)"FileFsFullSizeInformation";
        case FileFsObjectIdInformation:
            return (unsigned char *)"FileFsObjectIdInformation";
        case FileFsSizeInformation:
            return (unsigned char *)"FileFsSizeInformation";
        case FileFsVolumeInformation:
            return (unsigned char *)"FileFsVolumeInformation";
        default:
            return (unsigned char *)"UNKNOWN";
    }
}
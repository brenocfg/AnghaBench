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
typedef  enum comclass_miscfields { ____Placeholder_comclass_miscfields } comclass_miscfields ;
typedef  int DWORD ;

/* Variables and functions */
#define  DVASPECT_CONTENT 131 
#define  DVASPECT_DOCPRINT 130 
#define  DVASPECT_ICON 129 
#define  DVASPECT_THUMBNAIL 128 
 int MiscStatus ; 
 int MiscStatusContent ; 
 int MiscStatusDocPrint ; 
 int MiscStatusIcon ; 
 int MiscStatusThumbnail ; 

__attribute__((used)) static inline enum comclass_miscfields dvaspect_to_miscfields(DWORD aspect)
{
    switch (aspect)
    {
    case DVASPECT_CONTENT:
        return MiscStatusContent;
    case DVASPECT_THUMBNAIL:
        return MiscStatusThumbnail;
    case DVASPECT_ICON:
        return MiscStatusIcon;
    case DVASPECT_DOCPRINT:
        return MiscStatusDocPrint;
    default:
        return MiscStatus;
    };
}
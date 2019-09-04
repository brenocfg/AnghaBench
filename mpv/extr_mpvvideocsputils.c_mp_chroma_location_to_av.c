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
typedef  enum mp_chroma_location { ____Placeholder_mp_chroma_location } mp_chroma_location ;

/* Variables and functions */
 int AVCHROMA_LOC_CENTER ; 
 int AVCHROMA_LOC_LEFT ; 
 int AVCHROMA_LOC_UNSPECIFIED ; 
#define  MP_CHROMA_CENTER 129 
#define  MP_CHROMA_LEFT 128 

int mp_chroma_location_to_av(enum mp_chroma_location mploc)
{
    switch (mploc) {
    case MP_CHROMA_LEFT:                return AVCHROMA_LOC_LEFT;
    case MP_CHROMA_CENTER:              return AVCHROMA_LOC_CENTER;
    default:                            return AVCHROMA_LOC_UNSPECIFIED;
    }
}
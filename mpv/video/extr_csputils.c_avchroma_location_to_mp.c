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
#define  AVCHROMA_LOC_CENTER 129 
#define  AVCHROMA_LOC_LEFT 128 
 int MP_CHROMA_AUTO ; 
 int MP_CHROMA_CENTER ; 
 int MP_CHROMA_LEFT ; 

enum mp_chroma_location avchroma_location_to_mp(int avloc)
{
    switch (avloc) {
    case AVCHROMA_LOC_LEFT:             return MP_CHROMA_LEFT;
    case AVCHROMA_LOC_CENTER:           return MP_CHROMA_CENTER;
    default:                            return MP_CHROMA_AUTO;
    }
}
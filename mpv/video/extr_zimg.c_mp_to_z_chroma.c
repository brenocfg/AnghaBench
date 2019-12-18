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
typedef  int /*<<< orphan*/  zimg_chroma_location_e ;
typedef  enum mp_chroma_location { ____Placeholder_mp_chroma_location } mp_chroma_location ;

/* Variables and functions */
#define  MP_CHROMA_CENTER 129 
#define  MP_CHROMA_LEFT 128 
 int /*<<< orphan*/  ZIMG_CHROMA_CENTER ; 
 int /*<<< orphan*/  ZIMG_CHROMA_LEFT ; 

__attribute__((used)) static zimg_chroma_location_e mp_to_z_chroma(enum mp_chroma_location cl)
{
    switch (cl) {
    case MP_CHROMA_LEFT:        return ZIMG_CHROMA_LEFT;
    case MP_CHROMA_CENTER:      return ZIMG_CHROMA_CENTER;
    default:                    return ZIMG_CHROMA_LEFT;
    }
}
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
 int MPV_ERROR_PROPERTY_ERROR ; 
 int MPV_ERROR_PROPERTY_FORMAT ; 
 int MPV_ERROR_PROPERTY_NOT_FOUND ; 
 int MPV_ERROR_PROPERTY_UNAVAILABLE ; 
#define  M_PROPERTY_ERROR 133 
#define  M_PROPERTY_INVALID_FORMAT 132 
#define  M_PROPERTY_NOT_IMPLEMENTED 131 
#define  M_PROPERTY_OK 130 
#define  M_PROPERTY_UNAVAILABLE 129 
#define  M_PROPERTY_UNKNOWN 128 

__attribute__((used)) static int translate_property_error(int errc)
{
    switch (errc) {
    case M_PROPERTY_OK:                 return 0;
    case M_PROPERTY_ERROR:              return MPV_ERROR_PROPERTY_ERROR;
    case M_PROPERTY_UNAVAILABLE:        return MPV_ERROR_PROPERTY_UNAVAILABLE;
    case M_PROPERTY_NOT_IMPLEMENTED:    return MPV_ERROR_PROPERTY_ERROR;
    case M_PROPERTY_UNKNOWN:            return MPV_ERROR_PROPERTY_NOT_FOUND;
    case M_PROPERTY_INVALID_FORMAT:     return MPV_ERROR_PROPERTY_FORMAT;
    // shouldn't happen
    default:                            return MPV_ERROR_PROPERTY_ERROR;
    }
}
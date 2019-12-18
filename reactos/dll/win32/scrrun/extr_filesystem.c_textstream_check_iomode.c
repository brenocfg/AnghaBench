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
struct textstream {scalar_t__ mode; } ;
typedef  enum iotype { ____Placeholder_iotype } iotype ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ForAppending ; 
 scalar_t__ ForReading ; 
 scalar_t__ ForWriting ; 
 int IORead ; 

__attribute__((used)) static BOOL textstream_check_iomode(struct textstream *This, enum iotype type)
{
    if (type == IORead)
        return This->mode == ForWriting || This->mode == ForAppending;
    else
        return This->mode == ForReading;
}
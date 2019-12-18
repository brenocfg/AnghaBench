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
typedef  int /*<<< orphan*/  VIDEODISPLAYMODE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ MmAllocateMemory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PpcVideoGetBufferSize () ; 
 int /*<<< orphan*/  VideoTextMode ; 
 scalar_t__ video_mem ; 

VIDEODISPLAYMODE PpcVideoSetDisplayMode( char *DisplayMode, BOOLEAN Init ) {
    //printf( "DisplayMode: %s %s\n", DisplayMode, Init ? "true" : "false" );
    if( Init && !video_mem ) {
    video_mem = MmAllocateMemory( PpcVideoGetBufferSize() );
    }
    return VideoTextMode;
}
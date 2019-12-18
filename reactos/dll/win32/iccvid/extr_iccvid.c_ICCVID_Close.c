#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dwMagic; scalar_t__ cvinfo; } ;
typedef  int LRESULT ;
typedef  TYPE_1__ ICCVID_Info ;

/* Variables and functions */
 scalar_t__ ICCVID_MAGIC ; 
 int /*<<< orphan*/  free_cvinfo (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static LRESULT ICCVID_Close( ICCVID_Info *info )
{
    if( (info==NULL) || (info->dwMagic!=ICCVID_MAGIC) )
        return 0;
    if( info->cvinfo )
        free_cvinfo( info->cvinfo );
    heap_free( info );
    return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prefs ;
struct TYPE_5__ {int autoFlush; } ;
typedef  TYPE_1__ LZ4F_preferences_t ;

/* Variables and functions */
 size_t LZ4F_compressBound_internal (size_t,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_INIT (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 size_t maxFHSize ; 

size_t LZ4F_compressFrameBound(size_t srcSize, const LZ4F_preferences_t* preferencesPtr)
{
    LZ4F_preferences_t prefs;
    size_t const headerSize = maxFHSize;      /* max header size, including optional fields */

    if (preferencesPtr!=NULL) prefs = *preferencesPtr;
    else MEM_INIT(&prefs, 0, sizeof(prefs));
    prefs.autoFlush = 1;

    return headerSize + LZ4F_compressBound_internal(srcSize, &prefs, 0);;
}
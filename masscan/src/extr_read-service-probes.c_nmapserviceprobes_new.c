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
struct NmapServiceProbeList {char const* filename; } ;

/* Variables and functions */
 struct NmapServiceProbeList* CALLOC (int,int) ; 

__attribute__((used)) static struct NmapServiceProbeList *
nmapserviceprobes_new(const char *filename)
{
    struct NmapServiceProbeList *result;
    
    result = CALLOC(1, sizeof(*result));
    result->filename = filename;

    return result;
}
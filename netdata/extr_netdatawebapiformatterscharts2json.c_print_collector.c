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
struct collector {char* plugin; char* module; } ;
struct array_printer {scalar_t__ c; int /*<<< orphan*/ * wb; } ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 

int print_collector(void *entry, void *data) {
    struct array_printer *ap = (struct array_printer *)data;
    BUFFER *wb = ap->wb;
    struct collector *col=(struct collector *) entry;
    if(ap->c) buffer_strcat(wb, ",");
    buffer_strcat(wb, "\n\t\t{\n\t\t\t\"plugin\": \"");
    buffer_strcat(wb, col->plugin);
    buffer_strcat(wb, "\",\n\t\t\t\"module\": \"");
    buffer_strcat(wb, col->module);
    buffer_strcat(wb, "\"\n\t\t}");
    (ap->c)++;
    return 0;
}
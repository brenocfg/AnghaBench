#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct vo {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* query_format ) (struct vo*,int) ;} ;

/* Variables and functions */
 int IMGFMT_END ; 
 int IMGFMT_START ; 
 int /*<<< orphan*/  stub1 (struct vo*,int) ; 

__attribute__((used)) static void run_query_format(void *p)
{
    void **pp = p;
    struct vo *vo = pp[0];
    uint8_t *list = pp[1];
    for (int format = IMGFMT_START; format < IMGFMT_END; format++)
        list[format - IMGFMT_START] = vo->driver->query_format(vo, format);
}
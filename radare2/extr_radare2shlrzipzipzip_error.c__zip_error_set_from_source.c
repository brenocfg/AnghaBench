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
struct zip_source {int dummy; } ;
struct zip_error {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int,int) ; 
 int /*<<< orphan*/  zip_source_error (struct zip_source*,int*,int*) ; 

void
_zip_error_set_from_source(struct zip_error *err, struct zip_source *src)
{
    int ze, se;
    
    zip_source_error(src, &ze, &se);
    _zip_error_set(err, ze, se);
}
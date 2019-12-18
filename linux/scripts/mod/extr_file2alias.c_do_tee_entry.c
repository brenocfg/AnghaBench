#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* b; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  tee_client_device_id ; 
 TYPE_1__ uuid ; 

__attribute__((used)) static int do_tee_entry(const char *filename, void *symval, char *alias)
{
	DEF_FIELD(symval, tee_client_device_id, uuid);

	sprintf(alias, "tee:%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		uuid.b[0], uuid.b[1], uuid.b[2], uuid.b[3], uuid.b[4],
		uuid.b[5], uuid.b[6], uuid.b[7], uuid.b[8], uuid.b[9],
		uuid.b[10], uuid.b[11], uuid.b[12], uuid.b[13], uuid.b[14],
		uuid.b[15]);

	add_wildcard(alias);
	return 1;
}
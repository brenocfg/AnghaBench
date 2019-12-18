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
struct usbentry {int dummy; } ;

/* Variables and functions */
 struct usbentry* find_device (int*,int*,int*,int*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_devices () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  reset_device (struct usbentry*) ; 
 int sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 

int main(int argc, char **argv)
{
	int id1, id2;
	struct usbentry *dev;

	if ((argc == 2) && (sscanf(argv[1], "%3d/%3d", &id1, &id2) == 2))
	{
		dev = find_device(&id1, &id2, NULL, NULL, NULL);
	}
	else if ((argc == 2) && (sscanf(argv[1], "%4x:%4x", &id1, &id2) == 2))
	{
		dev = find_device(NULL, NULL, &id1, &id2, NULL);
	}
	else if ((argc == 2) && strlen(argv[1]) < 128)
	{
		dev = find_device(NULL, NULL, NULL, NULL, argv[1]);
	}
	else
	{
		printf("Usage:\n"
		       "  usbreset PPPP:VVVV - reset by product and vendor id\n"
		       "  usbreset BBB/DDD   - reset by bus and device number\n"
		       "  usbreset \"Product\" - reset by product name\n\n"
		       "Devices:\n");
		list_devices();
		return 1;
	}

	if (!dev)
	{
		fprintf(stderr, "No such device found\n");
		return 1;
	}

	reset_device(dev);
	return 0;
}
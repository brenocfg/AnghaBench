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
struct descriptor {char* name; char* connection; struct descriptor* next; } ;

/* Variables and functions */
 struct descriptor* descriptors ; 
 void* mm_alloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

void
add_descriptor(char *name, char *connection)
{
	struct descriptor *new;

	if (name[0] != '"')
		return;

	new = (struct descriptor *) mm_alloc(sizeof(struct descriptor));

	new->next = descriptors;
	new->name = mm_alloc(strlen(name) + 1);
	strcpy(new->name, name);
	if (connection)
	{
		new->connection = mm_alloc(strlen(connection) + 1);
		strcpy(new->connection, connection);
	}
	else
		new->connection = connection;
	descriptors = new;
}
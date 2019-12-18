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
struct cidr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cidr_push (struct cidr*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct cidr* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct cidr*,struct cidr*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct cidr * cidr_clone(struct cidr *a)
{
	struct cidr *b = malloc(sizeof(*b));

	if (!b)
	{
		fprintf(stderr, "out of memory\n");
		exit(255);
	}

	memcpy(b, a, sizeof(*b));
	cidr_push(b);

	return b;
}
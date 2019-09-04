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
struct Queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct Queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

struct Queue *
queue_create(void)
{
    struct Queue *queue;
    queue = (struct Queue *)malloc(sizeof(*queue));
    if (queue == NULL) {
        fprintf(stderr, "%s: out of memory error\n", "smack");
        exit(1);
    }
    memset(queue, 0, sizeof(*queue));
    return queue;
}
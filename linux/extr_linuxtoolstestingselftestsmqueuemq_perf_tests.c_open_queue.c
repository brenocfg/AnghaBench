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
struct mq_attr {int dummy; } ;
struct TYPE_3__ {int mq_flags; char* mq_maxmsg; char* mq_msgsize; char* mq_curmsgs; } ;

/* Variables and functions */
 int DEFFILEMODE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 scalar_t__ mq_getattr (int,TYPE_1__*) ; 
 int mq_open (char*,int,int,struct mq_attr*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int queue ; 
 char* queue_path ; 
 TYPE_1__ result ; 
 int /*<<< orphan*/  shutdown (int,char*,int) ; 

__attribute__((used)) static inline void open_queue(struct mq_attr *attr)
{
	int flags = O_RDWR | O_EXCL | O_CREAT | O_NONBLOCK;
	int perms = DEFFILEMODE;

	queue = mq_open(queue_path, flags, perms, attr);
	if (queue == -1)
		shutdown(1, "mq_open()", __LINE__);
	if (mq_getattr(queue, &result))
		shutdown(1, "mq_getattr()", __LINE__);
	printf("\n\tQueue %s created:\n", queue_path);
	printf("\t\tmq_flags:\t\t\t%s\n", result.mq_flags & O_NONBLOCK ?
	       "O_NONBLOCK" : "(null)");
	printf("\t\tmq_maxmsg:\t\t\t%lu\n", result.mq_maxmsg);
	printf("\t\tmq_msgsize:\t\t\t%lu\n", result.mq_msgsize);
	printf("\t\tmq_curmsgs:\t\t\t%lu\n", result.mq_curmsgs);
}
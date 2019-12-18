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
typedef  int u8 ;
struct tomoyo_io_buffer {int type; int readbuf_size; int writebuf_size; struct tomoyo_io_buffer* read_buf; void* write_buf; int /*<<< orphan*/ * write; int /*<<< orphan*/ * poll; int /*<<< orphan*/ * read; int /*<<< orphan*/  io_sem; } ;
struct file {int f_mode; struct tomoyo_io_buffer* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
#define  TOMOYO_AUDIT 136 
#define  TOMOYO_DOMAINPOLICY 135 
#define  TOMOYO_EXCEPTIONPOLICY 134 
#define  TOMOYO_MANAGER 133 
#define  TOMOYO_PROCESS_STATUS 132 
#define  TOMOYO_PROFILE 131 
#define  TOMOYO_QUERY 130 
#define  TOMOYO_STAT 129 
#define  TOMOYO_VERSION 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tomoyo_io_buffer*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_notify_gc (struct tomoyo_io_buffer*,int) ; 
 int /*<<< orphan*/ * tomoyo_poll_log ; 
 int /*<<< orphan*/ * tomoyo_poll_query ; 
 int /*<<< orphan*/  tomoyo_query_observers ; 
 int /*<<< orphan*/ * tomoyo_read_domain ; 
 int /*<<< orphan*/ * tomoyo_read_exception ; 
 int /*<<< orphan*/ * tomoyo_read_log ; 
 int /*<<< orphan*/ * tomoyo_read_manager ; 
 int /*<<< orphan*/ * tomoyo_read_pid ; 
 int /*<<< orphan*/ * tomoyo_read_profile ; 
 int /*<<< orphan*/ * tomoyo_read_query ; 
 int /*<<< orphan*/ * tomoyo_read_stat ; 
 int /*<<< orphan*/ * tomoyo_read_version ; 
 int /*<<< orphan*/ * tomoyo_write_answer ; 
 int /*<<< orphan*/ * tomoyo_write_domain ; 
 int /*<<< orphan*/ * tomoyo_write_exception ; 
 int /*<<< orphan*/ * tomoyo_write_manager ; 
 int /*<<< orphan*/ * tomoyo_write_pid ; 
 int /*<<< orphan*/ * tomoyo_write_profile ; 
 int /*<<< orphan*/ * tomoyo_write_stat ; 

int tomoyo_open_control(const u8 type, struct file *file)
{
	struct tomoyo_io_buffer *head = kzalloc(sizeof(*head), GFP_NOFS);

	if (!head)
		return -ENOMEM;
	mutex_init(&head->io_sem);
	head->type = type;
	switch (type) {
	case TOMOYO_DOMAINPOLICY:
		/* /sys/kernel/security/tomoyo/domain_policy */
		head->write = tomoyo_write_domain;
		head->read = tomoyo_read_domain;
		break;
	case TOMOYO_EXCEPTIONPOLICY:
		/* /sys/kernel/security/tomoyo/exception_policy */
		head->write = tomoyo_write_exception;
		head->read = tomoyo_read_exception;
		break;
	case TOMOYO_AUDIT:
		/* /sys/kernel/security/tomoyo/audit */
		head->poll = tomoyo_poll_log;
		head->read = tomoyo_read_log;
		break;
	case TOMOYO_PROCESS_STATUS:
		/* /sys/kernel/security/tomoyo/.process_status */
		head->write = tomoyo_write_pid;
		head->read = tomoyo_read_pid;
		break;
	case TOMOYO_VERSION:
		/* /sys/kernel/security/tomoyo/version */
		head->read = tomoyo_read_version;
		head->readbuf_size = 128;
		break;
	case TOMOYO_STAT:
		/* /sys/kernel/security/tomoyo/stat */
		head->write = tomoyo_write_stat;
		head->read = tomoyo_read_stat;
		head->readbuf_size = 1024;
		break;
	case TOMOYO_PROFILE:
		/* /sys/kernel/security/tomoyo/profile */
		head->write = tomoyo_write_profile;
		head->read = tomoyo_read_profile;
		break;
	case TOMOYO_QUERY: /* /sys/kernel/security/tomoyo/query */
		head->poll = tomoyo_poll_query;
		head->write = tomoyo_write_answer;
		head->read = tomoyo_read_query;
		break;
	case TOMOYO_MANAGER:
		/* /sys/kernel/security/tomoyo/manager */
		head->write = tomoyo_write_manager;
		head->read = tomoyo_read_manager;
		break;
	}
	if (!(file->f_mode & FMODE_READ)) {
		/*
		 * No need to allocate read_buf since it is not opened
		 * for reading.
		 */
		head->read = NULL;
		head->poll = NULL;
	} else if (!head->poll) {
		/* Don't allocate read_buf for poll() access. */
		if (!head->readbuf_size)
			head->readbuf_size = 4096 * 2;
		head->read_buf = kzalloc(head->readbuf_size, GFP_NOFS);
		if (!head->read_buf) {
			kfree(head);
			return -ENOMEM;
		}
	}
	if (!(file->f_mode & FMODE_WRITE)) {
		/*
		 * No need to allocate write_buf since it is not opened
		 * for writing.
		 */
		head->write = NULL;
	} else if (head->write) {
		head->writebuf_size = 4096 * 2;
		head->write_buf = kzalloc(head->writebuf_size, GFP_NOFS);
		if (!head->write_buf) {
			kfree(head->read_buf);
			kfree(head);
			return -ENOMEM;
		}
	}
	/*
	 * If the file is /sys/kernel/security/tomoyo/query , increment the
	 * observer counter.
	 * The obserber counter is used by tomoyo_supervisor() to see if
	 * there is some process monitoring /sys/kernel/security/tomoyo/query.
	 */
	if (type == TOMOYO_QUERY)
		atomic_inc(&tomoyo_query_observers);
	file->private_data = head;
	tomoyo_notify_gc(head, true);
	return 0;
}
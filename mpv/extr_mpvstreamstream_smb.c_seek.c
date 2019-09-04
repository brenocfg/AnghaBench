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
struct priv {int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {struct priv* priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_lock ; 
 scalar_t__ smbc_lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seek(stream_t *s,int64_t newpos) {
  struct priv *p = s->priv;
  pthread_mutex_lock(&smb_lock);
  off_t size = smbc_lseek(p->fd,newpos,SEEK_SET);
  pthread_mutex_unlock(&smb_lock);
  if(size<0) {
    return 0;
  }
  return 1;
}
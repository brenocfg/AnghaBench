#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct TYPE_4__ {size_t init_data_len; int part; int has_qlog; int /*<<< orphan*/  log_name; int /*<<< orphan*/  route_name; int /*<<< orphan*/  lock; int /*<<< orphan*/ * init_data; } ;
typedef  TYPE_1__ LoggerState ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  strftime (int /*<<< orphan*/ ,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 

void logger_init(LoggerState *s, const char* log_name, const uint8_t* init_data, size_t init_data_len, bool has_qlog) {
  memset(s, 0, sizeof(*s));
  if (init_data) {
    s->init_data = (uint8_t*)malloc(init_data_len);
    assert(s->init_data);
    memcpy(s->init_data, init_data, init_data_len);
    s->init_data_len = init_data_len;
  }

  umask(0);

  pthread_mutex_init(&s->lock, NULL);

  s->part = -1;
  s->has_qlog = has_qlog;

  time_t rawtime = time(NULL);
  struct tm timeinfo;
  localtime_r(&rawtime, &timeinfo);

  strftime(s->route_name, sizeof(s->route_name),
           "%Y-%m-%d--%H-%M-%S", &timeinfo);
  snprintf(s->log_name, sizeof(s->log_name), "%s", log_name);
}
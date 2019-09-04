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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  enum crawler_run_type { ____Placeholder_crawler_run_type } crawler_run_type ;
typedef  enum crawler_result_type { ____Placeholder_crawler_result_type } crawler_result_type ;

/* Variables and functions */
 int COLD_LRU ; 
 int CRAWLER_BADCLASS ; 
 int CRAWLER_ERROR ; 
 int CRAWLER_NOTSTARTED ; 
 int CRAWLER_OK ; 
 int CRAWLER_RUNNING ; 
 int HOT_LRU ; 
 int MAX_NUMBER_OF_SLAB_CLASSES ; 
 int POWER_LARGEST ; 
 int POWER_SMALLEST ; 
 int TEMP_LRU ; 
 int WARM_LRU ; 
 int /*<<< orphan*/  lru_crawler_lock ; 
 int lru_crawler_start (int*,unsigned int,int const,int /*<<< orphan*/ *,void*,int const) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_strtoul (char*,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 

enum crawler_result_type lru_crawler_crawl(char *slabs, const enum crawler_run_type type,
        void *c, const int sfd, unsigned int remaining) {
    char *b = NULL;
    uint32_t sid = 0;
    int starts = 0;
    uint8_t tocrawl[POWER_LARGEST];

    /* FIXME: I added this while debugging. Don't think it's needed? */
    memset(tocrawl, 0, sizeof(uint8_t) * POWER_LARGEST);
    if (strcmp(slabs, "all") == 0) {
        for (sid = 0; sid < POWER_LARGEST; sid++) {
            tocrawl[sid] = 1;
        }
    } else {
        for (char *p = strtok_r(slabs, ",", &b);
             p != NULL;
             p = strtok_r(NULL, ",", &b)) {

            if (!safe_strtoul(p, &sid) || sid < POWER_SMALLEST
                    || sid >= MAX_NUMBER_OF_SLAB_CLASSES) {
                pthread_mutex_unlock(&lru_crawler_lock);
                return CRAWLER_BADCLASS;
            }
            tocrawl[sid | TEMP_LRU] = 1;
            tocrawl[sid | HOT_LRU] = 1;
            tocrawl[sid | WARM_LRU] = 1;
            tocrawl[sid | COLD_LRU] = 1;
        }
    }

    starts = lru_crawler_start(tocrawl, remaining, type, NULL, c, sfd);
    if (starts == -1) {
        return CRAWLER_RUNNING;
    } else if (starts == -2) {
        return CRAWLER_ERROR; /* FIXME: not very helpful. */
    } else if (starts) {
        return CRAWLER_OK;
    } else {
        return CRAWLER_NOTSTARTED;
    }
}
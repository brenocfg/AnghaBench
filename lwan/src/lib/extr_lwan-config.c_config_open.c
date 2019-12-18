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
struct config {int dummy; } ;

/* Variables and functions */
 struct config* config_init_data (struct config*,void*,size_t) ; 
 struct config* config_open_path (char const*,void**,size_t*) ; 

struct config *config_open(const char *path)
{
    struct config *config;
    void *data;
    size_t len;

    config = config_open_path(path, &data, &len);
    return config ? config_init_data(config, data, len) : NULL;
}
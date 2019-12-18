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
struct vo {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  MP_ERR (struct vo*,char*,char*) ; 
 int /*<<< orphan*/  MP_INFO (struct vo*,char*,char const*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ mkdir (char const*,int) ; 
 char* mp_strerror (scalar_t__) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static bool checked_mkdir(struct vo *vo, const char *buf)
{
    MP_INFO(vo, "Creating output directory '%s'...\n", buf);
    if (mkdir(buf, 0755) < 0) {
        char *errstr = mp_strerror(errno);
        if (errno == EEXIST) {
            struct stat stat_p;
            if (stat(buf, &stat_p ) == 0 && S_ISDIR(stat_p.st_mode))
                return true;
        }
        MP_ERR(vo, "Error creating output directory: %s\n", errstr);
        return false;
    }
    return true;
}
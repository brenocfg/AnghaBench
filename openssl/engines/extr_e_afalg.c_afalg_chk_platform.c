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
struct utsname {int /*<<< orphan*/ * release; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFALG_F_AFALG_CHK_PLATFORM ; 
 int /*<<< orphan*/  AFALG_R_FAILED_TO_GET_PLATFORM_INFO ; 
 int /*<<< orphan*/  AFALG_R_KERNEL_DOES_NOT_SUPPORT_ASYNC_AFALG ; 
 int /*<<< orphan*/  AFALG_R_SOCKET_CREATE_FAILED ; 
 int /*<<< orphan*/  AFALGerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AF_ALG ; 
 int /*<<< orphan*/  ALG_ERR (char*,int,int,int) ; 
 scalar_t__ KERNEL_VERSION (int,int,int) ; 
 int K_MAJ ; 
 int K_MIN1 ; 
 int K_MIN2 ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strtok (int /*<<< orphan*/ *,char*) ; 
 int uname (struct utsname*) ; 

__attribute__((used)) static int afalg_chk_platform(void)
{
    int ret;
    int i;
    int kver[3] = { -1, -1, -1 };
    int sock;
    char *str;
    struct utsname ut;

    ret = uname(&ut);
    if (ret != 0) {
        AFALGerr(AFALG_F_AFALG_CHK_PLATFORM,
                 AFALG_R_FAILED_TO_GET_PLATFORM_INFO);
        return 0;
    }

    str = strtok(ut.release, ".");
    for (i = 0; i < 3 && str != NULL; i++) {
        kver[i] = atoi(str);
        str = strtok(NULL, ".");
    }

    if (KERNEL_VERSION(kver[0], kver[1], kver[2])
        < KERNEL_VERSION(K_MAJ, K_MIN1, K_MIN2)) {
        ALG_ERR("ASYNC AFALG not supported this kernel(%d.%d.%d)\n",
                 kver[0], kver[1], kver[2]);
        ALG_ERR("ASYNC AFALG requires kernel version %d.%d.%d or later\n",
                 K_MAJ, K_MIN1, K_MIN2);
        AFALGerr(AFALG_F_AFALG_CHK_PLATFORM,
                 AFALG_R_KERNEL_DOES_NOT_SUPPORT_ASYNC_AFALG);
        return 0;
    }

    /* Test if we can actually create an AF_ALG socket */
    sock = socket(AF_ALG, SOCK_SEQPACKET, 0);
    if (sock == -1) {
        AFALGerr(AFALG_F_AFALG_CHK_PLATFORM, AFALG_R_SOCKET_CREATE_FAILED);
        return 0;
    }
    close(sock);

    return 1;
}
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
struct sockaddr_alg {char* salg_type; char* salg_name; int /*<<< orphan*/  salg_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_3__ {int bfd; int sfd; } ;
typedef  TYPE_1__ afalg_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  AFALG_F_AFALG_CREATE_SK ; 
 int /*<<< orphan*/  AFALG_R_SOCKET_ACCEPT_FAILED ; 
 int /*<<< orphan*/  AFALG_R_SOCKET_BIND_FAILED ; 
 int /*<<< orphan*/  AFALG_R_SOCKET_CREATE_FAILED ; 
 int /*<<< orphan*/  AFALGerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AF_ALG ; 
 int ALG_MAX_SALG_NAME ; 
 int ALG_MAX_SALG_TYPE ; 
 int /*<<< orphan*/  ALG_PERR (char*,char*,int) ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_alg*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int afalg_create_sk(afalg_ctx *actx, const char *ciphertype,
                                const char *ciphername)
{
    struct sockaddr_alg sa;
    int r = -1;

    actx->bfd = actx->sfd = -1;

    memset(&sa, 0, sizeof(sa));
    sa.salg_family = AF_ALG;
    strncpy((char *) sa.salg_type, ciphertype, ALG_MAX_SALG_TYPE);
    sa.salg_type[ALG_MAX_SALG_TYPE-1] = '\0';
    strncpy((char *) sa.salg_name, ciphername, ALG_MAX_SALG_NAME);
    sa.salg_name[ALG_MAX_SALG_NAME-1] = '\0';

    actx->bfd = socket(AF_ALG, SOCK_SEQPACKET, 0);
    if (actx->bfd == -1) {
        ALG_PERR("%s(%d): Failed to open socket : ", __FILE__, __LINE__);
        AFALGerr(AFALG_F_AFALG_CREATE_SK, AFALG_R_SOCKET_CREATE_FAILED);
        goto err;
    }

    r = bind(actx->bfd, (struct sockaddr *)&sa, sizeof(sa));
    if (r < 0) {
        ALG_PERR("%s(%d): Failed to bind socket : ", __FILE__, __LINE__);
        AFALGerr(AFALG_F_AFALG_CREATE_SK, AFALG_R_SOCKET_BIND_FAILED);
        goto err;
    }

    actx->sfd = accept(actx->bfd, NULL, 0);
    if (actx->sfd < 0) {
        ALG_PERR("%s(%d): Socket Accept Failed : ", __FILE__, __LINE__);
        AFALGerr(AFALG_F_AFALG_CREATE_SK, AFALG_R_SOCKET_ACCEPT_FAILED);
        goto err;
    }

    return 1;

 err:
    if (actx->bfd >= 0)
        close(actx->bfd);
    if (actx->sfd >= 0)
        close(actx->sfd);
    actx->bfd = actx->sfd = -1;
    return 0;
}
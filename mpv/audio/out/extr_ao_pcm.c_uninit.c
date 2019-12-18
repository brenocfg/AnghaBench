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
struct priv {int data_length; int /*<<< orphan*/  fp; scalar_t__ waveheader; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ FILE_TYPE_DISK ; 
 scalar_t__ GetFileType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ _get_osfhandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_wave_header (struct ao*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    struct priv *priv = ao->priv;

    if (priv->waveheader) {    // Rewrite wave header
        bool broken_seek = false;
#ifdef __MINGW32__
        // Windows, in its usual idiocy "emulates" seeks on pipes so it always
        // looks like they work. So we have to detect them brute-force.
        broken_seek = FILE_TYPE_DISK !=
            GetFileType((HANDLE)_get_osfhandle(_fileno(priv->fp)));
#endif
        if (broken_seek || fseek(priv->fp, 0, SEEK_SET) != 0)
            MP_ERR(ao, "Could not seek to start, WAV size headers not updated!\n");
        else {
            if (priv->data_length > 0xfffff000) {
                MP_ERR(ao, "File larger than allowed for "
                       "WAV files, may play truncated!\n");
                priv->data_length = 0xfffff000;
            }
            write_wave_header(ao, priv->fp, priv->data_length);
        }
    }
    fclose(priv->fp);
}
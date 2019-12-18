#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double play_dir; int fps; } ;
struct priv {int has_broken_decoded_pts; double first_packet_pdts; double pts; TYPE_2__ public; TYPE_1__* opt_cache; } ;
struct mp_image {double pts; } ;
struct MPOpts {scalar_t__ correct_pts; } ;
struct TYPE_3__ {struct MPOpts* opts; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_WARN (struct priv*,char*,...) ; 

__attribute__((used)) static void correct_video_pts(struct priv *p, struct mp_image *mpi)
{
    struct MPOpts *opts = p->opt_cache->opts;

    mpi->pts *= p->public.play_dir;

    if (!opts->correct_pts || mpi->pts == MP_NOPTS_VALUE) {
        double fps = p->public.fps > 0 ? p->public.fps : 25;

        if (opts->correct_pts) {
            if (p->has_broken_decoded_pts <= 1) {
                MP_WARN(p, "No video PTS! Making something up. Using "
                        "%f FPS.\n", fps);
                if (p->has_broken_decoded_pts == 1)
                    MP_WARN(p, "Ignoring further missing PTS warnings.\n");
                p->has_broken_decoded_pts++;
            }
        }

        double frame_time = 1.0f / fps;
        double base = p->first_packet_pdts;
        mpi->pts = p->pts;
        if (mpi->pts == MP_NOPTS_VALUE) {
            mpi->pts = base == MP_NOPTS_VALUE ? 0 : base;
        } else {
            mpi->pts += frame_time;
        }
    }

    p->pts = mpi->pts;
}